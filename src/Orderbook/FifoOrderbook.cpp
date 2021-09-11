#include "TradingEngine/Orderbook/FifoOrderbook.h"

namespace TradingEngine::Orderbook {
	FifoOrderbook::FifoOrderbook(std::unique_ptr<RetrievalOrderbook> ob, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> test)
		: AbstractOrderbook(std::move(ob), std::move(test)) {};
	
	MatchOrderBookResult FifoOrderbook::match()
	{
		OrderBookResult obr = OrderBookResult();
		std::lock_guard<std::mutex> guard(ob_mutex);
		std::vector<std::shared_ptr<OrderbookEntry>> bids = orderbook_->getBidOrders();
		std::vector<std::shared_ptr<OrderbookEntry>> asks = orderbook_->getAskOrders();
		MatchResult matchResult = matchingAlgorithm_->match(bids, asks);
		//std::set<Fill, decltype(compareFill)> fullyFilledOrders;
		std::vector<Fill> fullyFilledOrders;
		std::vector<Fill> fills = matchResult.getFills();
		std::for_each(fills.begin(), fills.end(), [&](Fill f) {if (f.isCompleteFill_) fullyFilledOrders.push_back(f); });
		
		for (Fill fill : fullyFilledOrders)
		{
			obr.merge(orderbook_->removeOrder(Orders::CancelOrder(fill.orderBase_)));
		}
		
		return MatchOrderBookResult(matchResult, obr);
	}
}
