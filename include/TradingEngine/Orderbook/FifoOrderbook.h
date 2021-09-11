#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <set>
#include "TradingEngine/Orderbook/Orderbook.h"
#include <memory>

namespace TradingEngine::Orderbook {
	class FifoOrderbook : public MatchingOrderbook
	{
	public:
		FifoOrderbook(std::unique_ptr<RetrievalOrderbook> ob, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> test);

	};
}
