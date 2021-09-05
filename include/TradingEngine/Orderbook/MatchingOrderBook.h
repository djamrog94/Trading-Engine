#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/OrderBookResult.h"
#include "TradingEngine/Orderbook/MatchResult.h"

namespace TradingEngine::Orderbook {
	struct MatchOrderBookResult {
		MatchResult MatchResult;
		OrderBookResult OrderBookResult;
	};
	class MatchingOrderbook : OrderEntryOrderbook
	{
		MatchOrderBookResult match();
	};
}

