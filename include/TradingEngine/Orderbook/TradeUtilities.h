#pragma once
#include "TradingEngine/Orderbook/Trade.h"
#include "TradingEngine/Orderbook/Fill.h"
#include "TradingEngine/Orders/Order.h"
#include <string>
#include <time.h>
#include "TradingEngine/Orders/OrderCore.h"
namespace TradingEngine::Orderbook {

	struct TradeAndFills {
		Trade trade;
		Fill firstFill;
		Fill secondFill;
	};

	struct FillIds {
		long firstFillId;
		long secondFillId;
	};

	// singleton
	class TradeUtilities
	{
	public:
		static TradeUtilities& getInstance();
		TradeUtilities(TradeUtilities const&) = delete;
		void operator=(TradeUtilities const&) = delete;

		static TradeAndFills createTradeAndFills(Orders::Order bidOrder, Orders::Order askOrder, uint16_t fillQuantity, FillAllocationAlgorithm fillAlocAlgo);
		static FillIds getFillIds(long tradeNumber);
	private:
		TradeUtilities();
		long tradeNumber_;
	};

}