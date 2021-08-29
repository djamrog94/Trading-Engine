#pragma once
#include "TradingEngine/Orderbook/Limit.h"
#include "TradingEngine/Orders/Order.h"

namespace TradingEngine::Orderbook {
	class Limit;
	class OrderbookEntry
	{
	public:
		OrderbookEntry(Orders::Order currentOrder, Limit& parentLimit);
		OrderbookEntry(Orders::Order currentOrder, const Limit& parentLimit);
		Orders::Order getCurrent();
		Limit& getParentLimit();
		friend bool operator==(OrderbookEntry&, OrderbookEntry&);

		OrderbookEntry getNext();
	    OrderbookEntry getPrevious();

		void setNext(OrderbookEntry& next);
		void setPrevious(OrderbookEntry& prev);

		OrderbookEntry* Next;
		OrderbookEntry* Previous;

	private:
		Orders::Order currentOrder_;
		Limit& parentLimit_;
	};

	bool operator==(OrderbookEntry& lhs, OrderbookEntry& rhs)
	{
		return lhs == rhs;
	}

}
