#pragma once
#include "TradingEngine/Orderbook/OrderbookEntry.h"

namespace TradingEngine::Orderbook {
	class OrderbookEntry;
	class Limit
	{
	public:
		Limit();
		Limit(long price);
		long getPrice();
		OrderbookEntry getHead();
		OrderbookEntry getTail();

		void setPrice(long price);
		void setHead(OrderbookEntry& head);
		void setTail(OrderbookEntry& tail);

		long price_;
		OrderbookEntry* head_;
		OrderbookEntry* tail_;
	};

	class BidLimitComparer
	{
	public:
		int Compare(Limit x, Limit y)
		{
			if (x.price_ == y.price_) return 0;
			else if (x.price_ > y.price_) return 1;
			else return -1;
		}
	};

	class AskLimitComparer
	{
	public:
		int Compare(Limit x, Limit y)
		{
			if (x.price_ == y.price_) return 0;
			else if (x.price_ > y.price_) return 1;
			else return -1;
		}
	};
}
