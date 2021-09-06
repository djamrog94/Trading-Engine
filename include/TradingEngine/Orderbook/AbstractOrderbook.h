#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <mutex>

namespace TradingEngine::Orderbook {
	class AbstractOrderbook : public MatchingOrderbook
	{
	public:
		AbstractOrderbook(Orderbook orderbook, MatchingAlgorithm::FifoMatchingAlgorithm matchingAlgorithm);
		int getCount();
		OrderBookResult addOrder(Orders::Order order);
		OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		bool containsOrder(long orderId);
		Spread getSpread();
		virtual MatchOrderBookResult match() { return MatchOrderBookResult(); };

	protected:
		MatchingAlgorithm::FifoMatchingAlgorithm matchingAlgorithm_;
		Orderbook orderbook_;
		std::mutex ob_mutex;
	};
}

