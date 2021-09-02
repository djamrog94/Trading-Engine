#include "TradingEngine/Orderbook/MatchResult.h"

namespace TradingEngine::Orderbook {
	MatchResult::MatchResult() = default;
	
	void MatchResult::addTrade(Trade trade)
	{
		trades_.push_back(trade);
	}
	void MatchResult::addFill(Fill fill)
	{
		fill_.push_back(fill);
	}
	const std::vector<Trade> MatchResult::getTrades() 
	{
		return trades_;
	}
	const std::vector<Fill> MatchResult::getFills() 
	{
		return fill_;
	}
}
