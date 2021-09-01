#pragma once
#include "TradingEngine/Orderbook/OrderbookEntry.h"

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
		void setHead(OrderbookEntry& head);
		void setTail(OrderbookEntry& tail);

		long price_;
		mutable OrderbookEntry* head_;
		mutable OrderbookEntry* tail_;
	};
	
	inline bool operator==(const Limit& lhs, const Limit& rhs)
	{
		if (lhs.price_ == rhs.price_ && lhs.head_ == rhs.head_ && lhs.tail_ == rhs.tail_) return true;
		//if (lhs.price_ == rhs.price_) return true;
		return false;
	}

}
