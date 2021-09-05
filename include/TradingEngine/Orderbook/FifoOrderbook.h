#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/AbstractOrderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include <set>
namespace TradingEngine::Orderbook {
	class FifoOrderbook : public AbstractOrderbook
	{
		FifoOrderbook(RetrievalOrderbook ob);
		MatchOrderBookResult match();

	};
}
