#include "TradingEngine/Orderbook/FifoOrderbook.h"

namespace TradingEngine::Orderbook {
	FifoOrderbook::FifoOrderbook(std::unique_ptr<Orderbook> ob, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> test)
		: MatchingOrderbook(std::move(ob), std::move(test)) {};
	
}
