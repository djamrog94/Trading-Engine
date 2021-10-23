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

		std::shared_ptr<OrderbookEntry> Next;
		std::shared_ptr<OrderbookEntry> Previous;
		Orders::Order currentOrder_;

	private:
		std::shared_ptr<Limit> parentLimit_;
	};

	inline bool operator==(const OrderbookEntry& lhs, const OrderbookEntry& rhs)
	{
		if (lhs.currentOrder_ == rhs.currentOrder_) return true;
		return false;
	}

}
