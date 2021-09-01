#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include <map>
#include <vector>
#include <set>

namespace TradingEngine::Orderbook {
	const auto compareBid = [](Limit x, Limit y)
	{
		return x.price_ > y.price_;
	};
	const auto compareAsk = [](Limit x, Limit y)
	{
		return x.price_ < y.price_;
	};
	class Instrument{};
	class Orderbook : public RetrievalOrderbook
	{
	public:
		Orderbook();
		Orderbook(Instrument instrument);
		OrderBookResult addOrder(Orders::Order order);
		OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		bool containsOrder(long orderId);
		std::vector<OrderbookEntry> getAskOrders();
		std::vector<OrderbookEntry> getBidOrders();
		Spread getSpread();
		int getCount();

	private:
		
		template <typename T> static void addOrder(Orders::Order order, Limit& baseLimit, std::set<Limit, T>& limitLevels, std::map<long, OrderbookEntry>& internalBook);
		static void removeOrder(Orders::CancelOrder co, OrderbookEntry& obe, std::map<long, OrderbookEntry>& internalBook);
		static void removeOrder(long orderId, OrderbookEntry& obe, std::map<long, OrderbookEntry>& internalBook);

		Instrument instrument_;
		std::map<long, OrderbookEntry> orders_;
		std::set<Limit, decltype(compareBid)> bidLimits_;
		std::set<Limit, decltype(compareAsk)> askLimits_;

	};
}
