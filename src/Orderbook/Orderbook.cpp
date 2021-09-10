#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/ActionResultConversion.h"
#include "TradingEngine/Orderbook/Reject/RejectCreator.h"
namespace TradingEngine::Orderbook {

    Orderbook::Orderbook() : RetrievalOrderbook() {};
    Orderbook::Orderbook(Instrument instrument)
        : RetrievalOrderbook(), instrument_(instrument) {}

    OrderBookResult Orderbook::addOrder(Orders::Order order)
    {
        OrderBookResult ar = OrderBookResult();
        std::shared_ptr<Limit> baseLimit = std::make_shared<Limit>(order.price_);
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
            std::shared_ptr<OrderbookEntry> obe = mod->second;
            if (modifyOrder.isBuySide_ != (*obe).getCurrent().isBuySide_)
            {
                ar.AddRejection(Reject::RejectCreator::generateModyifyRejection(modifyOrder, Reject::rejectionReason::AttemptingToModifyWrongSide));
                return ar;
            }
            Orders::CancelOrder co = Orders::CancelOrder(modifyOrder);
            if (obe->currentOrder_.isBuySide_)
            {
                removeOrder(co, obe, bidLimits_, orders_);
            }
            else
            {
                removeOrder(co, obe, askLimits_, orders_);
            }
            Orders::Order ord = Orders::Order(modifyOrder);
            if (modifyOrder.isBuySide_) addOrder(ord, (*obe).getParentLimit(), bidLimits_, orders_);
            else addOrder(ord, (*obe).getParentLimit(), askLimits_, orders_);
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
            std::shared_ptr<OrderbookEntry> obe = can->second;
            if (obe->currentOrder_.isBuySide_)
            {
                removeOrder(cancelOrder, obe, bidLimits_, orders_);
            }
            else
            {
                removeOrder(cancelOrder, obe, askLimits_, orders_);
            }
            ar.AddCancelOrderStatus(ActionResultConversion::generateCancelOrderStatus(cancelOrder));
        }
        return ar;
    }

    bool Orderbook::containsOrder(long orderId)
    {
        return orders_.contains(orderId);
    }


    std::vector<std::shared_ptr<OrderbookEntry>> Orderbook::getAskOrders()
    {
        std::vector<std::shared_ptr<OrderbookEntry>> asks;
        asks.reserve(askLimits_.size());
        for (auto it : askLimits_)
        {
            std::shared_ptr<OrderbookEntry> listTraverse = (*it).head_;
            while (listTraverse)
            {
                asks.push_back(listTraverse);
                listTraverse = listTraverse->Next;
            }
        }
        return asks;
    }

    std::vector<std::shared_ptr<OrderbookEntry>> Orderbook::getBidOrders()
    {
        std::vector<std::shared_ptr<OrderbookEntry>> bids;
        bids.reserve(bidLimits_.size());
        for (auto it : bidLimits_)
        {
            std::shared_ptr<OrderbookEntry> listTraverse = (*it).head_;
            while (listTraverse != NULL)
            {
                bids.push_back(listTraverse);
                listTraverse = listTraverse->Next;
            }
        }
        return bids;
    }

    Spread Orderbook::getSpread()
    {
        boost::optional<long> bestAsk = NULL, bestBid = NULL;
        // in c# first element in sorted set and min are different, in c++ is this ok?
        if (!askLimits_.empty()) bestAsk = (*(*askLimits_.begin())).price_;
        if (!bidLimits_.empty()) bestBid = (*(*bidLimits_.begin())).price_;
        return Spread(bestAsk, bestBid);
    }

    int Orderbook::getCount()
    {
        return orders_.size();
    }

    template <typename T> 
    void Orderbook::addOrder(Orders::Order order, std::shared_ptr<Limit> baseLimit, std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook)
    {

        auto ll = limitLevels.find(baseLimit);
        if (ll != limitLevels.end())
        {
            std::shared_ptr<Limit> foundLimit = *ll;
            auto newEntry = std::make_shared<OrderbookEntry>(order, foundLimit);
            auto node = limitLevels.extract(ll);
            if ((*node.value()).head_ == NULL)
            {
                (*node.value()).head_ = newEntry;
                (*node.value()).tail_ = newEntry;
                //foundLimit.head_ = newEntry;
                //foundLimit.tail_ = newEntry;
            }
            else
            {
                auto tailProxy = (*node.value()).tail_;
                newEntry->Previous = tailProxy;
                tailProxy->Next = newEntry;
                (*node.value()).tail_ = newEntry;
            }
            limitLevels.insert(std::move(node));
			internalBook.insert(std::pair<long, std::shared_ptr<OrderbookEntry>>(order.getOrderId(), std::move(newEntry)));
        }
        else
        {
            //OrderbookEntry newEntry = OrderbookEntry(order, baseLimit);
            auto newEntry = std::make_shared<OrderbookEntry>(order, baseLimit);
            (*baseLimit).head_ = newEntry;
            (*baseLimit).tail_ = newEntry;
            limitLevels.insert(baseLimit);
			internalBook.insert(std::pair<long,std::shared_ptr<OrderbookEntry>>(order.getOrderId(), std::move(newEntry)));
            // need to get memory location of where obe is saved.
            //auto test = internalBook.find(order.getOrderId());
            //baseLimit.head_ = &test->second;
            //baseLimit.tail_ = &test->second;

            
        }
    }
    template <typename T>
    void Orderbook::removeOrder(Orders::CancelOrder co, std::shared_ptr<OrderbookEntry> obe,std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook)
    {
        removeOrder(co.getOrderId(), obe, limitLevels, internalBook);
    }

    template <typename T>
    void Orderbook::removeOrder(long orderId, std::shared_ptr<OrderbookEntry> obe,std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook)
    {
        // update obe within list
        if ((*obe).Previous != NULL and (*obe).Next != NULL)
        {
            // we are in middle of list
            (*obe).Previous->Next = (*obe).Next;
            (*obe).Next->Previous = (*obe).Previous;
        }
        // We are on tail
        else if ((*obe).Previous != NULL) (*obe).Previous->Next = NULL;
        // We are on head
        else if ((*obe).Next != NULL) (*obe).Next->Previous = NULL;

        // update limit within list
        //(*(*obe).getParentLimit()).head_
        if ( (*(*obe).getParentLimit()).head_ == obe && (*(*obe).getParentLimit()).tail_ == obe )
        {
            if (obe->getCurrent().isBuySide_)
            {
                limitLevels.erase((*obe).getParentLimit());
            }
            else
            {

            }
            //(*(*obe).getParentLimit()).head_ = NULL;
            //(*(*obe).getParentLimit()).tail_ = NULL;
        }

        else if ( (*(*obe).getParentLimit()).head_ == obe ) (*(*obe).getParentLimit()).head_ = (*obe).Next;
        else if ( (*(*obe).getParentLimit()).tail_ == obe) (*(*obe).getParentLimit()).tail_ = (*obe).Previous;
        
        internalBook.erase(orderId);
    }
}
