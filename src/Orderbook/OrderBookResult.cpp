#include "TradingEngine/Orderbook/OrderBookResult.h"

namespace TradingEngine::Orderbook {
	void OrderBookResult::merge(OrderBookResult obr)
	{
		AddNewOrderStatuses(obr.newOrderStatuses_);
		AddCancelOrderStatuses(obr.cancelOrderStatuses_);
		AddModifyOrderStatuses(obr.modifyOrderStatuses_);
		AddRejections(obr.rejections_);
	}

	void OrderBookResult::AddNewOrderStatuses(std::vector<OrderStatuses::NewOrderStatus>& os)
	{
		newOrderStatuses_.insert(newOrderStatuses_.end(), os.begin(), os.end());
	}

	void OrderBookResult::AddCancelOrderStatuses(std::vector<OrderStatuses::CancelOrderStatus>& os)
	{
		cancelOrderStatuses_.insert(cancelOrderStatuses_.end(), os.begin(), os.end());
	}

	void OrderBookResult::AddModifyOrderStatuses(std::vector<OrderStatuses::ModifyOrderStatus>& os)
	{
		modifyOrderStatuses_.insert(modifyOrderStatuses_.end(), os.begin(), os.end());
	}

	void OrderBookResult::AddRejections(std::vector<Reject::Rejection>& os)
	{
		rejections_.insert(rejections_.end(), os.begin(), os.end());
	}

	void OrderBookResult::AddNewOrderStatus(OrderStatuses::NewOrderStatus os)
	{
		newOrderStatuses_.push_back(os);
	}

	void OrderBookResult::AddCancelOrderStatus(OrderStatuses::CancelOrderStatus os)
	{
		cancelOrderStatuses_.push_back(os);
	}

	void OrderBookResult::AddModifyOrderStatus(OrderStatuses::ModifyOrderStatus os)
	{
		modifyOrderStatuses_.push_back(os);
	}

	void OrderBookResult::AddRejection(Reject::Rejection os)
	{
		rejections_.push_back(os);
	}

	const std::vector<OrderStatuses::NewOrderStatus> OrderBookResult::getNewOrderStatuses()
	{
		return newOrderStatuses_;
	}

	const std::vector<OrderStatuses::CancelOrderStatus> OrderBookResult::getCancelOrderStatuses()
	{
		return cancelOrderStatuses_;
	}

	const std::vector<OrderStatuses::ModifyOrderStatus> OrderBookResult::getModifyOrderStatuses()
	{
		return modifyOrderStatuses_;
	}

	const std::vector<Reject::Rejection> OrderBookResult::getRejections()
	{
		return rejections_;
	}

	bool OrderBookResult::hasNewOrderStatuses()
	{
		return !newOrderStatuses_.size();
	}

	bool OrderBookResult::hasCancelOrderStatuses()
	{
		return !cancelOrderStatuses_.size();
	}

	bool OrderBookResult::hasModifyOrderStatuses()
	{
		return !modifyOrderStatuses_.size();
	}

	bool OrderBookResult::hasRejections()
	{
		return !rejections_.size();
	}
}
