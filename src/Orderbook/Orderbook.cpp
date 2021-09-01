#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/ActionResultConversion.h"
#include "TradingEngine/Orderbook/Reject/RejectCreator.h"

namespace TradingEngine::Orderbook {

    Orderbook::Orderbook() = default;
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
            OrderbookEntry* listTraverse = it.head_;
            while (listTraverse)
            {
                asks.push_back(*listTraverse);
                listTraverse = listTraverse->Next;
            }
        }
        return asks;
    }

    std::vector<OrderbookEntry> Orderbook::getBidOrders()
    {
        std::vector<OrderbookEntry> bids;
        for (auto it : bidLimits_)
        {
            OrderbookEntry* listTraverse = it.head_;
            while (listTraverse != NULL)
            {
                bids.push_back(*listTraverse);
                listTraverse = listTraverse->Next;
            }
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

    int Orderbook::getCount()
    {
        return orders_.size();
    }

    template <typename T> 
    void Orderbook::addOrder(Orders::Order order, Limit& baseLimit, std::set<Limit, T>& limitLevels, std::map<long, OrderbookEntry>& internalBook)
    {

        auto ll = limitLevels.find(baseLimit);
        if (ll != limitLevels.end())
        {
            Limit foundLimit = *ll;
            OrderbookEntry newEntry = OrderbookEntry(order, foundLimit);
            if (foundLimit.head_ == NULL)
            {
                foundLimit.head_ = &newEntry;
                foundLimit.tail_ = &newEntry;
            }
            else
            {
                OrderbookEntry* tailProxy = foundLimit.tail_;
                newEntry.Previous = tailProxy;
                tailProxy->Next = &newEntry;
                foundLimit.tail_ = &newEntry;
            }
			internalBook.insert(std::pair<long, OrderbookEntry>(order.getOrderId(), newEntry));
        }
        else
        {
            OrderbookEntry newEntry = OrderbookEntry(order, baseLimit);
			internalBook.insert(std::pair<long, OrderbookEntry>(order.getOrderId(), std::move(newEntry)));
            // need to get memory location of where obe is saved.
            auto test = internalBook.find(order.getOrderId());
            baseLimit.head_ = &test->second;
            baseLimit.tail_ = &test->second;
            limitLevels.insert(baseLimit);

            
        }
    }

    void Orderbook::removeOrder(Orders::CancelOrder co, OrderbookEntry& obe, std::map<long, OrderbookEntry>& internalBook)
    {
        removeOrder(co.getOrderId(), obe, internalBook);
    }

    void Orderbook::removeOrder(long orderId, OrderbookEntry& obe, std::map<long, OrderbookEntry>& internalBook)
    {
        // update obe within list
        if (obe.Previous != NULL and obe.Next != NULL)
        {
            // we are in middle of list
            obe.Previous->Next = obe.Next;
            obe.Next->Previous = obe.Previous;
        }
        // We are on tail
        else if (obe.Previous != NULL) obe.Previous->Next = NULL;
        // We are on head
        else if (obe.Next != NULL) obe.Next->Previous = NULL;

        // update limit within list
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
