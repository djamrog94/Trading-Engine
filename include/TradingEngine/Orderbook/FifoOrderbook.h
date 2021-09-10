#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/AbstractOrderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <set>
#include "TradingEngine/Orderbook/Orderbook.h"

namespace TradingEngine::Orderbook {
	class FifoOrderbook : public AbstractOrderbook
	{
	public:
		FifoOrderbook(RetrievalOrderbook* ob, MatchingAlgorithm::MatchingAlgorithm* test);
		MatchOrderBookResult match();

	};
}
