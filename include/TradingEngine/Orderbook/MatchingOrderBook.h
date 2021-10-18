#pragma once
#include "TradingEngine/Orderbook/OrderEntryOrderbook.h"
#include "TradingEngine/Orderbook/MatchResult.h"
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
#include "TradingEngine/Orders/ModifyOrder.h"
#include <memory>
#include <mutex>
namespace TradingEngine::Orderbook {
	class MatchingOrderbook : public OrderEntryOrderbook
	{
	public:

		MatchingOrderbook(std::unique_ptr<RetrievalOrderbook> orderbook, std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm);
		int getCount();
		void addOrder(Orders::Order order);
		void changeOrder(Orders::ModifyOrder modifyOrder);
		void removeOrder(Orders::CancelOrder cancelOrder);
		Orders::ModifyOrderType getModifyOrderType(Orders::ModifyOrder modifyOrder);
		std::shared_ptr<OrderbookEntry> tryGetOrder(long orderId);
		bool containsOrder(long orderId);

		Spread getSpread();
		MatchResult match();

		//protected:
		std::unique_ptr<MatchingAlgorithm::MatchingAlgorithm> matchingAlgorithm_;
		std::unique_ptr<RetrievalOrderbook> orderbook_;
		std::mutex ob_mutex;
	};
}

