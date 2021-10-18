#include "TradingEngine/Orderbook/MatchingOrderbook.h"
namespace TradingEngine::Orderbook {
	MatchingOrderbook::MatchingOrderbook(std::unique_ptr<RetrievalOrderbook> orderbook, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm) 
		:orderbook_(std::move(orderbook)), matchingAlgorithm_(std::move(matchingAlgorithm)) {}
	int MatchingOrderbook::getCount()
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getCount();
	}

	void MatchingOrderbook::addOrder(Orders::Order order)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		orderbook_->addOrder(order);
	}
	void MatchingOrderbook::changeOrder(Orders::ModifyOrder modifyOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		orderbook_->changeOrder(modifyOrder);
	}
	void MatchingOrderbook::removeOrder(Orders::CancelOrder cancelOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		orderbook_->removeOrder(cancelOrder);
	}
	Orders::ModifyOrderType MatchingOrderbook::getModifyOrderType(Orders::ModifyOrder modifyOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getModifyOrderType(modifyOrder);
	}
	std::shared_ptr<OrderbookEntry> MatchingOrderbook::tryGetOrder(long orderId)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->tryGetOrder(orderId);
	}
	bool MatchingOrderbook::containsOrder(long orderId)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->containsOrder(orderId);
	}
	Spread MatchingOrderbook::getSpread()
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getSpread();
	}
	MatchResult MatchingOrderbook::match()
	{
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
			orderbook_->removeOrder(Orders::CancelOrder(fill.orderBase_));
		}
		return matchResult;
	}
}
