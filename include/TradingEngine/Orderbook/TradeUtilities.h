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

	//class TradeUtilities
	//{
	//	static long tradeNumber_;
	//public:
	//	static tradeUtilities createTradeAndFills(Orders::Order bidOrder, Orders::Order askOrder, uint16_t fillQuantity, Orderbook::FillAllocationAlgorithm fillAlocAlgo);
	//	static fillIds getFillIds(long tradeNumber);
	//	static std::string getTradeExecutionId(time_t tradeTime, long tradeNumber);
	//};

	// singleton
	class TradeUtilities
	{
	public:
		static TradeUtilities& getInstance();
		TradeUtilities(TradeUtilities const&) = delete;
		void operator=(TradeUtilities const&) = delete;

		static TradeAndFills createTradeAndFills(Orders::Order bidOrder, Orders::Order askOrder, uint16_t fillQuantity, Orderbook::FillAllocationAlgorithm fillAlocAlgo);
		static FillIds getFillIds(long tradeNumber);
		static std::string getTradeExecutionId(time_t tradeTime, long tradeNumber);
	private:
		TradeUtilities();
		long tradeNumber_;
	};

}

