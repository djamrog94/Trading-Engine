#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include <map>
#include <vector>
#include <set>
#include <memory>
namespace TradingEngine::Orderbook {
	const auto compareBid = [](std::shared_ptr<Limit> x, std::shared_ptr<Limit> y)
	{
		return (*x).price_ > (*y).price_;
	};
	const auto compareAsk = [](std::shared_ptr<Limit> x, std::shared_ptr<Limit> y)
	{
		return (*x).price_ < (*y).price_;
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
		
		template <typename T> static void addOrder(Orders::Order order, std::shared_ptr<Limit> baseLimit, std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);
		static void removeOrder(Orders::CancelOrder co, OrderbookEntry& obe, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);
		static void removeOrder(long orderId, OrderbookEntry& obe, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);

		Instrument instrument_;
		std::map<long, std::shared_ptr<OrderbookEntry>> orders_;
		std::set<std::shared_ptr<Limit>, decltype(compareBid)> bidLimits_;
		std::set<std::shared_ptr<Limit>, decltype(compareAsk)> askLimits_;

	};
}
