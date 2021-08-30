#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/ActionResultConversion.h"
#include "TradingEngine/Orderbook/Reject/RejectCreator.h"

namespace TradingEngine::Orderbook {
    Orderbook::Orderbook(Instrument instrument)
        : instrument_(instrument) {}

    OrderBookResult Orderbook::addOrder(Orders::Order order)
    {
        OrderBookResult ar = OrderBookResult();
        Limit baseLimit = Limit(order.price_);
        if (order.isBuySide_) addOrder(order, baseLimit, bidLimits_, orders_);
        else addOrder(order, baseLimit, askLimits_, orders_);
        ar.AddNewOrderStatus(ActionResultConversion::generateNewOrderStatus(order));
        return OrderBookResult();
    }

    OrderBookResult Orderbook::changeOrder(Orders::ModifyOrder modifyOrder)
    {
        OrderBookResult ar = OrderBookResult();
        auto mod = orders_.find(modifyOrder.getOrderId());
        
        // if order exists
        if (mod != orders_.end())
        {
            OrderbookEntry obe = mod->second;
            if (modifyOrder.isBuySide_ != obe.getCurrent().isBuySide_)
            {
                ar.AddRejection(Reject::RejectCreator::generateModyifyRejection(modifyOrder, Reject::rejectionReason::AttemptingToModifyWrongSide));
                return ar;
            }
            Orders::CancelOrder co = Orders::CancelOrder(modifyOrder);
            removeOrder(co, obe, orders_);
            Orders::Order ord = Orders::Order(modifyOrder);
            if (modifyOrder.isBuySide_) addOrder(ord, obe.getParentLimit(), bidLimits_, orders_);
           else addOrder(ord, obe.getParentLimit(), askLimits_, orders_);
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
            OrderbookEntry obe = can->second;
            removeOrder(cancelOrder, obe, orders_);
            ar.AddCancelOrderStatus(ActionResultConversion::generateCancelOrderStatus(cancelOrder));
        }
        return ar;
    }

    bool Orderbook::containsOrder(long orderId)
    {
        return orders_.contains(orderId);
    }


    std::vector<OrderbookEntry> Orderbook::getAskOrders()
    {
        std::vector<OrderbookEntry> asks;
        for (auto it : askLimits_)
        {
            asks.push_back(it.getHead());
        }
        return asks;
    }

    std::vector<OrderbookEntry> Orderbook::getBuyOrders()
    {
        std::vector<OrderbookEntry> bids;
        for (auto it : bidLimits_)
        {
            bids.push_back(it.getHead());
        }
        return bids;
    }

    Spread Orderbook::getSpread()
    {
        boost::optional<long> bestAsk = NULL, bestBid = NULL;
        // in c# first element in sorted set and min are different, in c++ is this ok?
        if (!askLimits_.empty()) bestAsk = (*askLimits_.begin()).price_;
        if (!bidLimits_.empty()) bestBid = (*bidLimits_.begin()).price_;
        return Spread(bestAsk, bestBid);
    }

    void Orderbook::addOrder(Orders::Order order, Limit baseLimit, std::set<Limit, decltype(compare)> limitLevels, std::map<long, OrderbookEntry> internalBook)
    {
        auto ll = limitLevels.find(baseLimit);
        if (ll != limitLevels.end())
        {
            //OrderbookEntry newEntry = OrderbookEntry(order, *ll);
            auto newLimit = limitLevels.extract(ll);
            OrderbookEntry newEntry = OrderbookEntry(order, newLimit.value());
            if (ll->head_ == NULL)
            {
                auto node = limitLevels.extract(ll);
                node.value().head_ = &newEntry;
                node.value().tail_ = &newEntry;
                limitLevels.insert(std::move(node));
            }
            else
            {
                OrderbookEntry tailProxy = *ll->tail_;
                newEntry.Previous = &tailProxy;
                tailProxy.Next = &newEntry;
            }
            internalBook.insert(std::pair<long, OrderbookEntry>(order.getOrderId(), newEntry));

        }
        else
        {
			OrderbookEntry newEntry = OrderbookEntry(order, baseLimit);
			baseLimit.head_ = &newEntry;
			baseLimit.tail_ = &newEntry;
			limitLevels.insert(baseLimit);
			internalBook.insert(std::pair<long, OrderbookEntry>(order.getOrderId(), newEntry));

        }
    
    }

    void Orderbook::removeOrder(Orders::CancelOrder co, OrderbookEntry obe, std::map<long, OrderbookEntry> internalBook)
    {
        removeOrder(co.getOrderId(), obe, internalBook);
    }

    void Orderbook::removeOrder(long orderId, OrderbookEntry obe, std::map<long, OrderbookEntry> internalBook)
    {
        if (obe.Previous != NULL) obe.Previous->Next = obe.Next;
        if (obe.Next != NULL) obe.Next->Previous = obe.Previous;

        if (*(obe.getParentLimit().head_) == obe && *(obe.getParentLimit().tail_) == obe)
        {
            obe.getParentLimit().head_ = NULL;
            obe.getParentLimit().tail_ = NULL;
        }
        else if (*(obe.getParentLimit().head_) == obe) obe.getParentLimit().head_ = obe.Next;
        else if (*(obe.getParentLimit().tail_) == obe) obe.getParentLimit().tail_ = obe.Previous;

        internalBook.erase(orderId);
    }
}
