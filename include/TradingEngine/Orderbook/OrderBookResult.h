#pragma once
#include <vector>
#include "TradingEngine/Orderbook/OrderStatuses/NewOrderStatus.h"
#include "TradingEngine/Orderbook/OrderStatuses/ModifyOrderStatus.h"
#include "TradingEngine/Orderbook/OrderStatuses/CancelOrderStatus.h"
#include "TradingEngine/Orderbook/Reject/Rejection.h"
namespace TradingEngine::Orderbook {
	class OrderBookResult
	{
	public:
		void merge(OrderBookResult obr);
		void AddNewOrderStatuses(std::vector<OrderStatuses::NewOrderStatus>& os);
		void AddCancelOrderStatuses(std::vector<OrderStatuses::CancelOrderStatus>& os);
		void AddModifyOrderStatuses(std::vector<OrderStatuses::ModifyOrderStatus>& os);
		void AddRejections(std::vector<Reject::Rejection>& os);
		void AddNewOrderStatus(OrderStatuses::NewOrderStatus os);
		void AddCancelOrderStatus(OrderStatuses::CancelOrderStatus os);
		void AddModifyOrderStatus(OrderStatuses::ModifyOrderStatus os);
		void AddRejection(Reject::Rejection os);

		const std::vector<OrderStatuses::NewOrderStatus> getNewOrderStatuses();
		const std::vector<OrderStatuses::CancelOrderStatus> getCancelOrderStatuses();
		const std::vector<OrderStatuses::ModifyOrderStatus> getModifyOrderStatuses();
		const std::vector<Reject::Rejection> getRejections();

		bool hasNewOrderStatuses();
		bool hasCancelOrderStatuses();
		bool hasModifyOrderStatuses();
		bool hasRejections();

	private:
		std::vector<OrderStatuses::NewOrderStatus> newOrderStatuses_ = std::vector<OrderStatuses::NewOrderStatus>();
		std::vector<OrderStatuses::CancelOrderStatus> cancelOrderStatuses_ = std::vector<OrderStatuses::CancelOrderStatus>();
		std::vector<OrderStatuses::ModifyOrderStatus> modifyOrderStatuses_ = std::vector<OrderStatuses::ModifyOrderStatus>();
		std::vector<Reject::Rejection> rejections_ = std::vector<Reject::Rejection>();
	};
}
