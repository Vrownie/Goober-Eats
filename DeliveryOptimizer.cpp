#include "provided.h"
#include <vector>
using namespace std;

class DeliveryOptimizerImpl
{
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm) {}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl() {}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(const GeoCoord& depot, vector<DeliveryRequest>& deliveries, double& oldCrowDistance, double& newCrowDistance) const
{
    oldCrowDistance = (deliveries.size() == 0) ? 0 : distanceEarthMiles(depot, deliveries[0].location);
    for(int i = 1; i < deliveries.size(); i++) {
        oldCrowDistance += distanceEarthMiles(deliveries[i-1].location, deliveries[i].location);
    }
    //do reordering here
    newCrowDistance = (deliveries.size() == 0) ? 0 : distanceEarthMiles(depot, deliveries[0].location);
    for(int i = 1; i < deliveries.size(); i++) {
        newCrowDistance += distanceEarthMiles(deliveries[i-1].location, deliveries[i].location);
    }
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
