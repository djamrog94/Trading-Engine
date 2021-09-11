#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Instrument/Security.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
namespace TradingEngine::Orderbook {
	class OrderbookFactory
	{
	public:

		static MatchingOrderbook createOrderbook(Instrument::Security inst);
	};
}
