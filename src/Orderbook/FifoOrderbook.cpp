#include "TradingEngine/Orderbook/FifoOrderbook.h"

namespace TradingEngine::Orderbook {
	FifoOrderbook::FifoOrderbook(RetrievalOrderbook ob)
		: AbstractOrderbook(ob, MatchingAlgorithm::FifoMatchingAlgorithm::getMatchingAlgorithm()) {}
	
	MatchOrderBookResult FifoOrderbook::match()
	{
		OrderBookResult obr = OrderBookResult();
		std::lock_guard<std::mutex> guard(ob_mutex);
		std::vector<std::shared_ptr<OrderbookEntry>> bids = orderbook_.getBidOrders();
		std::vector<std::shared_ptr<OrderbookEntry>> asks = orderbook_.getAskOrders();
		MatchResult matchResult = matchingAlgorithm_.match(bids, asks);
		std::set<Fill, decltype(compareFill)> fullyFilledOrders;
		std::for_each(matchResult.getFills().begin(), matchResult.getFills().end(), [&](Fill f) {if (f.isCompleteFill_) fullyFilledOrders.insert(f); });
		
		for (Fill fill : fullyFilledOrders)
		{
			obr.merge(orderbook_.removeOrder(Orders::CancelOrder(fill.orderBase_)));
		}
		
		return MatchOrderBookResult(matchResult, obr);
	}
}
