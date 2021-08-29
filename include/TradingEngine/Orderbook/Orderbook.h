#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include <map>
#include <vector>
#include <set>
namespace TradingEngine::Orderbook {
	class Instrument{};
	class Orderbook : RetrievalOrderbook
	{
	public:
		Orderbook(Instrument instrument);
		OrderBookResult addOrder(Orders::Order order);
		OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		bool containsOrder(long orderId);
		std::vector<OrderbookEntry> getAskOrders();
		std::vector<OrderbookEntry> getBuyOrders();
		Spread getSpread();

	private:
		static void addOrder(Orders::Order order, Limit baseLimit, std::set<Limit,BidLimitComparer> limitLevels, std::map<long, OrderbookEntry> internalBook);
		static void addOrder(Orders::Order order, Limit baseLimit, std::set<Limit,AskLimitComparer> limitLevels, std::map<long, OrderbookEntry> internalBook);
		static void removeOrder(Orders::CancelOrder co, OrderbookEntry obe, std::map<long, OrderbookEntry> internalBook);
		static void removeOrder(long orderId, OrderbookEntry obe, std::map<long, OrderbookEntry> internalBook);

		Instrument instrument_;
		std::map<long, OrderbookEntry> orders_;
		std::set<Limit,BidLimitComparer> bidLimits_;
		std::set<Limit,AskLimitComparer> askLimits_;

	};
}
