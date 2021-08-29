#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/OrderBookResult.h"

namespace TradingEngine::Orderbook {
	struct MatchOrderBookResult {
		//MatchResult MatchResult;
		OrderBookResult OrderBookResult;
	};
	class MatchingOrderBook : OrderEntryOrderbook
	{
		MatchOrderBookResult Match();
	};
}

