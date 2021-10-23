#pragma once
#include "Trade.h"
#include "Fill.h"
#include <vector>
namespace TradingEngine::Orderbook {
	class MatchResult
	{
	public:
		MatchResult();
		void addTrade(Trade trade);
		void addFill(Fill fill);
		const std::vector<Trade> getTrades();
		const std::vector<Fill> getFills();
	private:
		std::vector<Trade> trades_;
		std::vector<Fill> fill_;

	};
}