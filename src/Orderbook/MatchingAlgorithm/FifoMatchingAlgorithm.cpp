#include "TradingEngine/Orderbook/MatchingAlgorithm/FifoMatchingAlgorithm.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"

namespace TradingEngine::Orderbook::MatchingAlgorithm {
	FifoMatchingAlgorithm::FifoMatchingAlgorithm() = default;

	MatchResult FifoMatchingAlgorithm::match(std::vector<std::shared_ptr<OrderbookEntry>>& bids, std::vector<std::shared_ptr<OrderbookEntry>>& asks)
	{
		MatchResult matchResult = MatchResult();
		if (bids.size() == 0 || asks.size() == 0)
			return matchResult;
		std::shared_ptr<OrderbookEntry> orderToMatchAsk = *(asks.begin());
		std::shared_ptr<OrderbookEntry> orderToMatchBid = *(bids.begin());

		do
		{
			if ((*orderToMatchAsk).getCurrent().price_ > (*orderToMatchBid).getCurrent().price_)
			{
				break;
			}
			uint16_t remainingQuantityBid = (*orderToMatchBid).getCurrent().currentQuantity_;
			if (remainingQuantityBid == 0)
			{
				orderToMatchBid = (*orderToMatchBid).Next;
				continue;
			}
			uint16_t remainingQuantityAsk = (*orderToMatchAsk).getCurrent().currentQuantity_;
			if (remainingQuantityAsk == 0)
			{
				orderToMatchAsk = (*orderToMatchAsk).Next;
				continue;
			}
			uint16_t fillQuantity = std::min(remainingQuantityBid, remainingQuantityAsk);
			(*orderToMatchBid).currentOrder_.DecreaseQuantity(fillQuantity);
			(*orderToMatchAsk).currentOrder_.DecreaseQuantity(fillQuantity);

			Orderbook::TradeAndFills tradesAndFills = TradeUtilities::createTradeAndFills((*orderToMatchBid).getCurrent(), (*orderToMatchAsk).getCurrent(), fillQuantity, FillAllocationAlgorithm::Fifo);
			matchResult.addFill(tradesAndFills.firstFill);
			matchResult.addFill(tradesAndFills.secondFill);
			matchResult.addTrade(tradesAndFills.trade);

			if (tradesAndFills.firstFill.isCompleteFill_)
				orderToMatchBid = (*orderToMatchBid).Next;
			if (tradesAndFills.secondFill.isCompleteFill_)
				orderToMatchAsk = (*orderToMatchAsk).Next;

		} while (orderToMatchBid != NULL && orderToMatchAsk != NULL);
		
		return matchResult;
	}
}
