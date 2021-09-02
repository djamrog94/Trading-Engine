#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include <map>
#include <vector>
#include <set>

namespace TradingEngine::Orderbook {
	const auto compareBid = [](long x, long y)
	{
		return x > y;
	};
	const auto compareAsk = [](long x, long y)
	{
		return x < y;
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
		std::vector<Orders::Order> getAskOrders();
		std::vector<Orders::Order> getBidOrders();
		Spread getSpread();
		int getCount();

	private:
		
		template <typename T> static void addOrder(Orders::Order order, std::map<long, std::vector<Orders::Order*>, T>& limitLevels, std::map<long, Orders::Order>& internalBook);
		template <typename T> static void removeOrder(Orders::CancelOrder co, std::map<long, std::vector<Orders::Order*>, T>& limitLevel, std::map<long, Orders::Order>& internalBook);

		Instrument instrument_;
		std::map<long, Orders::Order> orders_;
		std::map<long, std::vector<Orders::Order*>, decltype(compareBid)> bidLimits_;
		std::map<long, std::vector<Orders::Order*>, decltype(compareAsk)> askLimits_;

	};
}
