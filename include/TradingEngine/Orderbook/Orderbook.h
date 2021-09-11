#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Instrument/Security.h"
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
	class Orderbook : public RetrievalOrderbook
	{
	public:
		//Orderbook();
		Orderbook(Instrument::Security security);
		OrderBookResult addOrder(Orders::Order order);
		OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		bool containsOrder(long orderId);
		std::vector<std::shared_ptr<OrderbookEntry>> getAskOrders();
		std::vector<std::shared_ptr<OrderbookEntry>> getBidOrders();
		Spread getSpread();
		int getCount();

	private:
		
		template <typename T> static void addOrder(Orders::Order order, std::shared_ptr<Limit> baseLimit, std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);
		template <typename T> static void removeOrder(Orders::CancelOrder co, std::shared_ptr<OrderbookEntry> obe,std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);
		template <typename T> static void removeOrder(long orderId, std::shared_ptr<OrderbookEntry> obe,std::set<std::shared_ptr<Limit>, T>& limitLevels, std::map<long, std::shared_ptr<OrderbookEntry>>& internalBook);

		Instrument::Security security_;
		std::map<long, std::shared_ptr<OrderbookEntry>> orders_;
		std::set<std::shared_ptr<Limit>, decltype(compareBid)> bidLimits_;
		std::set<std::shared_ptr<Limit>, decltype(compareAsk)> askLimits_;

	};
}
