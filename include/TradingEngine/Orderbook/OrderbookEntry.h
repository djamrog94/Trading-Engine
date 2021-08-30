#pragma once
#include "TradingEngine/Orderbook/Limit.h"
#include "TradingEngine/Orders/Order.h"

namespace TradingEngine::Orderbook {
	class Limit;
	class OrderbookEntry
	{
	public:
		OrderbookEntry(Orders::Order currentOrder, Limit& parentLimit);
		Orders::Order getCurrent();
		Limit& getParentLimit();
		friend bool operator==(const OrderbookEntry& lhs, const OrderbookEntry& rhs);

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

	inline bool operator==(const OrderbookEntry& lhs, const OrderbookEntry& rhs)
	{
		//if (lhs.Next == rhs.Next && lhs.Previous == rhs.Previous && lhs.currentOrder_ == rhs.currentOrder_ && lhs.parentLimit_ == rhs.parentLimit_) return true;
		if (lhs.currentOrder_ == rhs.currentOrder_) return true;
		return false;
	}

}
