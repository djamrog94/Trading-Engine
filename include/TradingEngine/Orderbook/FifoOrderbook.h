#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <set>
#include <memory>

namespace TradingEngine::Orderbook {
	class FifoOrderbook : public MatchingOrderbook
	{
	public:
		FifoOrderbook(std::unique_ptr<Orderbook> ob, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> test);

	};
}
