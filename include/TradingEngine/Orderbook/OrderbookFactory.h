#pragma once
#include "TradingEngine/Orderbook/MatchingOrderbook.h"
#include "TradingEngine/Instrument/Security.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include "TradingEngine/Orderbook/Orderbook.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
namespace TradingEngine::Orderbook {
	class OrderbookFactory
	{
	public:

		static MatchingOrderbook createOrderbook(Instrument::Security inst);
	};
}
