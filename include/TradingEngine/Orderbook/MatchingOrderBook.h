#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/OrderBookResult.h"
#include "TradingEngine/Orderbook/MatchResult.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include <memory>
#include <mutex>
namespace TradingEngine::Orderbook {
	struct MatchOrderBookResult {
		MatchResult MatchResult;
		OrderBookResult OrderBookResult;
	};
	class MatchingOrderbook : OrderEntryOrderbook
	{
	public:
		MatchOrderBookResult match();

		MatchingOrderbook(std::unique_ptr<RetrievalOrderbook> orderbook, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm);
		int getCount();
		OrderBookResult addOrder(Orders::Order order);
		OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		bool containsOrder(long orderId);
		Spread getSpread();
		virtual MatchOrderBookResult match() { return MatchOrderBookResult(); };

		//protected:
		std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm_;
		std::unique_ptr<RetrievalOrderbook> orderbook_;
		std::mutex ob_mutex;
	};
}

