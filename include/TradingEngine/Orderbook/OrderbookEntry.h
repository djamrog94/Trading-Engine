#pragma once
#include "TradingEngine/Orderbook/Limit.h"
#include "TradingEngine/Orders/Order.h"
#include <memory>

namespace TradingEngine::Orderbook {
	class Limit;
	class OrderbookEntry
	{
	public:
		OrderbookEntry(Orders::Order currentOrder, std::shared_ptr<Limit> parentLimit);
		Orders::Order getCurrent();
		std::shared_ptr<Limit> getParentLimit();
		friend bool operator==(const OrderbookEntry& lhs, const OrderbookEntry& rhs);

		OrderbookEntry getNext();
	    OrderbookEntry getPrevious();

		//void setNext(OrderbookEntry& next);
		//void setPrevious(OrderbookEntry& prev);

		std::shared_ptr<OrderbookEntry> Next;
		std::shared_ptr<OrderbookEntry> Previous;

	private:
		Orders::Order currentOrder_;
		std::shared_ptr<Limit> parentLimit_;
	};

	inline bool operator==(const OrderbookEntry& lhs, const OrderbookEntry& rhs)
	{
		//if (lhs.Next == rhs.Next && lhs.Previous == rhs.Previous && lhs.currentOrder_ == rhs.currentOrder_ && lhs.parentLimit_ == rhs.parentLimit_) return true;
		if (lhs.currentOrder_ == rhs.currentOrder_) return true;
		return false;
	}

}
