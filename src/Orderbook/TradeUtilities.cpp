#include "TradingEngine/Orderbook/TradeUtilities.h"

namespace TradingEngine::Orderbook {

	TradeUtilities::TradeUtilities() : tradeNumber_(0) {};
	TradeUtilities& TradeUtilities::getInstance()
	{
		static TradeUtilities instance;
		return instance;
	}
	TradeAndFills TradeUtilities::createTradeAndFills(Orders::Order bidOrder, Orders::Order askOrder, uint16_t fillQuantity, Orderbook::FillAllocationAlgorithm fillAlocAlgo)
	{
		
		Trade newTrade = Trade(bidOrder, fillQuantity);
		FillIds ids = getFillIds(newTrade.getTradeNumber());
		Orders::OrderCore orderFirst = Orders::OrderCore(bidOrder);
		Orders::OrderCore orderSecond = Orders::OrderCore(askOrder);
		Fill firstFill = Fill(orderFirst, fillAlocAlgo, fillQuantity, ids.firstFillId, bidOrder.currentQuantity_ == 0 ? true : false, newTrade.executionId_);
		Fill secondFill = Fill(orderSecond, fillAlocAlgo, fillQuantity, ids.secondFillId, askOrder.currentQuantity_ == 0 ? true : false, newTrade.executionId_);
		
		TradeAndFills tf{newTrade,firstFill,secondFill};
		return tf;
	}
	FillIds TradeUtilities::getFillIds(long tradeNumber)
	{
		FillIds fillids{2 * tradeNumber, 2*tradeNumber +1};
		return fillids;
	}
	//std::string TradeUtilities::getTradeExecutionId(time_t tradeTime, long tradeNumber)
	//{
	//	return std::string();
	//}
}
