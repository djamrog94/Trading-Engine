#pragma once
#include "TradingEngine/Orderbook/MatchResult.h"
#include "TradingEngine/Orderbook/OrderbookEntry.h"
namespace TradingEngine::Orderbook::MatchingAlgorithm {
	class MatchingAlgorithm
	{
	public:
		virtual Orderbook::MatchResult match(std::vector<std::shared_ptr<OrderbookEntry>> bids, std::vector<std::shared_ptr<OrderbookEntry>> asks) { return Orderbook::MatchResult(); };
	};
}

