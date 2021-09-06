#pragma once
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include "TradingEngine/Orderbook/TradeUtilities.h"

namespace TradingEngine::Orderbook::MatchingAlgorithm {
	class FifoMatchingAlgorithm : public MatchingAlgorithm
	{
	public:
		FifoMatchingAlgorithm();
		static FifoMatchingAlgorithm getMatchingAlgorithm();
		MatchResult match(std::vector<std::shared_ptr<OrderbookEntry>>& bids, std::vector<std::shared_ptr<OrderbookEntry>>& asks);
	};
}

