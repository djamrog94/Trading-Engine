#include "TradingEngine/Orderbook/OrderbookEntry.h"

namespace TradingEngine::Orderbook {

	OrderbookEntry::OrderbookEntry(Orders::Order currentOrder, std::shared_ptr<Limit> parentLimit)
		: currentOrder_(currentOrder), parentLimit_(parentLimit), Next(NULL), Previous(NULL) {}

	Orders::Order OrderbookEntry::getCurrent()
	{
		return currentOrder_;
	}
	std::shared_ptr<Limit> OrderbookEntry::getParentLimit()
	{
		return parentLimit_;
	}

	OrderbookEntry OrderbookEntry::getNext()
	{
		return *Next;
    }
	OrderbookEntry OrderbookEntry::getPrevious()
	{
		return *Previous;
	}
	//void OrderbookEntry::setNext(OrderbookEntry& next)
	//{
	//	Next = &next;
	//}
	//void OrderbookEntry::setPrevious(OrderbookEntry& prev)
	//{
	//	Previous = &prev;
	//}
}
