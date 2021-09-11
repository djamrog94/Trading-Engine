#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <mutex>
#include <memory>
namespace TradingEngine::Orderbook {
	class AbstractOrderbook : public MatchingOrderbook
	{
	public:
		AbstractOrderbook(std::unique_ptr<RetrievalOrderbook> orderbook, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm);
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

