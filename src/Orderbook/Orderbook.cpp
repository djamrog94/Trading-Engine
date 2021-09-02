#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/ActionResultConversion.h"
#include "TradingEngine/Orderbook/Reject/RejectCreator.h"
using Order = TradingEngine::Orders::Order;
using ModifyOrder = TradingEngine::Orders::ModifyOrder;
using CancelOrder = TradingEngine::Orders::CancelOrder;

namespace TradingEngine::Orderbook {

    Orderbook::Orderbook() = default;
    Orderbook::Orderbook(Instrument instrument)
        : instrument_(instrument) {}

    OrderBookResult Orderbook::addOrder(Order order)
    {
        OrderBookResult ar = OrderBookResult();
        if (order.isBuySide_) addOrder(order, bidLimits_, orders_);
        else addOrder(order, askLimits_, orders_);
        ar.AddNewOrderStatus(ActionResultConversion::generateNewOrderStatus(order));
        return OrderBookResult();
    }

    OrderBookResult Orderbook::changeOrder(ModifyOrder modifyOrder)
    {
        OrderBookResult ar = OrderBookResult();
        auto mod = orders_.find(modifyOrder.getOrderId());
        
        // if order exists
        if (mod != orders_.end())
        {
            Orders::Order order = mod->second;
            if (modifyOrder.isBuySide_ != order.isBuySide_)
            {
                ar.AddRejection(Reject::RejectCreator::generateModyifyRejection(modifyOrder, Reject::rejectionReason::AttemptingToModifyWrongSide));
                return ar;
            }
            CancelOrder co = CancelOrder(modifyOrder);
            if (modifyOrder.isBuySide_) removeOrder(co, bidLimits_, orders_);
            else removeOrder(co, askLimits_, orders_);
            Order ord = Order(modifyOrder);
            if (modifyOrder.isBuySide_) addOrder(ord, bidLimits_, orders_);
            else addOrder(ord, askLimits_, orders_);
        }
        else
        {
            ar.AddRejection(Reject::RejectCreator::generateModyifyRejection(modifyOrder, Reject::rejectionReason::OrderNotFound));
            return ar;
        }
        ar.AddModifyOrderStatus(ActionResultConversion::generateModifyOrderStatus(modifyOrder));
        return ar;
    }

    OrderBookResult Orderbook::removeOrder(Orders::CancelOrder cancelOrder)
    {
        OrderBookResult ar = OrderBookResult();
        auto can = orders_.find(cancelOrder.getOrderId());
        
        // if order exists
        if (can != orders_.end())
        {
            Order order = can->second;
            if (order.isBuySide_) removeOrder(cancelOrder, bidLimits_, orders_);
            else removeOrder(cancelOrder, askLimits_, orders_);
            ar.AddCancelOrderStatus(ActionResultConversion::generateCancelOrderStatus(cancelOrder));
        }
        return ar;
    }

    bool Orderbook::containsOrder(long orderId)
    {
        return orders_.contains(orderId);
    }


    std::vector<Order> Orderbook::getAskOrders()
    {
        std::vector<Order> asks;
        for (auto it : askLimits_)
        {
            for (auto listIt : it.second)
            {
                asks.push_back(*listIt);
            }
        }
        return asks;
    }

    std::vector<Order> Orderbook::getBidOrders()
    {
        std::vector<Order> bids;
        for (auto it : bidLimits_)
        {
            for (auto listIt : it.second)
            {
                bids.push_back(*listIt);
            }
        }
        return bids;
    }

    Spread Orderbook::getSpread()
    {
        boost::optional<long> bestAsk = NULL, bestBid = NULL;
        // in c# first element in sorted set and min are different, in c++ is this ok?
        if (!askLimits_.empty()) bestAsk = (*askLimits_.begin()).first;
        if (!bidLimits_.empty()) bestBid = (*bidLimits_.begin()).first;
        return Spread(bestAsk, bestBid);
    }

    int Orderbook::getCount()
    {
        return orders_.size();
    }

    template <typename T> 
    void Orderbook::addOrder(Orders::Order order, std::map<long, std::vector<Orders::Order*>, T>& limitLevels, std::map<long, Orders::Order>& internalBook)
    {
        // does that price already exist in limit book
        long baseLimit = order.price_;
        internalBook.insert(std::pair<long, Order>(order.getOrderId(), order));
        auto test = internalBook.find(order.getOrderId());
        Order* order_ptr = &test->second;
        auto ll = limitLevels.find(baseLimit);
        if (ll != limitLevels.end())
        {
            ll->second.push_back(order_ptr);
        }
        else
        {
            std::vector<Order*> limitOrders{ order_ptr };
            limitLevels.insert(std::pair<long, std::vector<Order*>>(baseLimit, limitOrders));
        }
    }
    template <typename T>
    void Orderbook::removeOrder(Orders::CancelOrder co, std::map<long, std::vector<Orders::Order*>, T>& limitLevel, std::map<long, Order>& internalBook)
    {
        auto it = internalBook.find(co.getOrderId());
        Order* od = &it->second;
        long price = od->price_;
        auto limitOrder = limitLevel.find(price);
        if (limitOrder != limitLevel.end())
        {
            auto order = std::find(limitLevel[price].begin(), limitLevel[price].end(), od);
            if (order != limitLevel[price].end())
                limitLevel[price].erase(order);
            if (limitLevel[price].size() == 0) limitLevel.erase(price);
        }
        internalBook.erase(co.getOrderId());
    }
}
