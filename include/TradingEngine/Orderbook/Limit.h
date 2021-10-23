#pragma once
#include "TradingEngine/Orderbook/OrderbookEntry.h"
#include <memory>

namespace TradingEngine::Orderbook {
	class OrderbookEntry;
	class Limit
	{
	public:
		Limit(long price);
		long getPrice();
		OrderbookEntry getHead();
		OrderbookEntry getTail();
		friend bool operator==(const Limit& lhs, const Limit& rhs);

		void setPrice(long price);

		long price_;
		mutable std::shared_ptr<OrderbookEntry> head_;
		mutable std::shared_ptr<OrderbookEntry> tail_;
	};
	
	inline bool operator==(const Limit& lhs, const Limit& rhs)
	{
		if (lhs.price_ == rhs.price_ && lhs.head_ == rhs.head_ && lhs.tail_ == rhs.tail_)
			return true;
		return false;
	}

}
