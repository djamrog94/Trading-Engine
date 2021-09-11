#include "TradingEngine/Orderbook/MatchingOrderbook.h"
namespace TradingEngine::Orderbook {
	MatchingOrderbook::MatchingOrderbook(std::unique_ptr<RetrievalOrderbook> orderbook, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm) 
		:orderbook_(std::move(orderbook)), matchingAlgorithm_(std::move(matchingAlgorithm)) {}
	int MatchingOrderbook::getCount()
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getCount();
	}

	OrderBookResult MatchingOrderbook::addOrder(Orders::Order order)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->addOrder(order);
	}
	OrderBookResult MatchingOrderbook::changeOrder(Orders::ModifyOrder modifyOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->changeOrder(modifyOrder);
	}
	OrderBookResult MatchingOrderbook::removeOrder(Orders::CancelOrder cancelOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->removeOrder(cancelOrder);
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
}
