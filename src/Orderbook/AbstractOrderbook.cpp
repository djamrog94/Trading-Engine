#include "TradingEngine/Orderbook/AbstractOrderbook.h"
#include "TradingEngine/Orderbook/Orderbook.h"

namespace TradingEngine::Orderbook {
	AbstractOrderbook::AbstractOrderbook(RetrievalOrderbook* orderbook, MatchingAlgorithm::MatchingAlgorithm* matchingAlgorithm)
		: orderbook_(orderbook), matchingAlgorithm_(matchingAlgorithm) {}

	int AbstractOrderbook::getCount()
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getCount();
	}

	OrderBookResult AbstractOrderbook::addOrder(Orders::Order order)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->addOrder(order);
	}
	OrderBookResult AbstractOrderbook::changeOrder(Orders::ModifyOrder modifyOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->changeOrder(modifyOrder);
	}
	OrderBookResult AbstractOrderbook::removeOrder(Orders::CancelOrder cancelOrder)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->removeOrder(cancelOrder);
	}
	bool AbstractOrderbook::containsOrder(long orderId)
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->containsOrder(orderId);
	}
	Spread AbstractOrderbook::getSpread()
	{
		std::lock_guard<std::mutex> guard(ob_mutex);
		return orderbook_->getSpread();
	}
}
