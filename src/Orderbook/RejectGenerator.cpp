#include "TradingEngine/Orderbook/RejectGenerator.h"

namespace TradingEngine::Orderbook {
	bool RejectGenerator::tryRejectNewOrder(Orders::Order order, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection)
	{
		if (!orderbook.containsOrder(order.getOrderId()))
		{
			
			rejection = Reject::RejectCreator::generateOrderCoreReject(order, Reject::rejectionReason::OrderIdAlreadyPresent);
			return true;
		}
		return false;
	}
	bool RejectGenerator::tryRejectModifyOrder(Orders::ModifyOrder modifyOrder, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection)
	{
		auto modifyOrderType = orderbook.getModifyOrderType(modifyOrder);
		std::shared_ptr<OrderbookEntry> it = orderbook.tryGetOrder(modifyOrder.getOrderId());
		if (modifyOrderType == Orders::ModifyOrderType::NoChange)
		{
			rejection = Reject::RejectCreator::generateOrderCoreReject(modifyOrder, Reject::rejectionReason::ModifyOrderDoesntModifyAnything);
			return true;
		}
		else if (modifyOrderType == Orders::ModifyOrderType::Unknown)
		{
			rejection = Reject::RejectCreator::generateOrderCoreReject(modifyOrder, Reject::rejectionReason::OrderNotFound);
			return true;
		}
		else if (!orderbook.containsOrder(modifyOrder.getOrderId()))
		{
			rejection = Reject::RejectCreator::generateOrderCoreReject(modifyOrder, Reject::rejectionReason::OrderNotFound);
			return true;
		}
		else if ((*it).getCurrent().isBuySide_ != modifyOrder.isBuySide_)
		{
			rejection = Reject::RejectCreator::generateOrderCoreReject(modifyOrder, Reject::rejectionReason::AttemptingToModifyWrongSide);
			return true;
		}

		return false;
	}
	bool RejectGenerator::tryRejectCancelOrder(Orders::CancelOrder cancelOrder, RetrievalOrderbook orderbook, Orderbook::Reject::Rejection& rejection)
	{
		if (!orderbook.containsOrder(cancelOrder.getOrderId()))
		{
			
			rejection = std::move(Reject::RejectCreator::generateOrderCoreReject(cancelOrder, Reject::rejectionReason::OrderNotFound));
			return true;
		}
		return false;
	}
}
