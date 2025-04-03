#pragma once

#include "physics/core.h"

namespace physics {

	/**
	 * A rigid body is the basic simulation object in the physics core.
	 */
	class RigidBody
	{
	protected:
		/** Holds the inverse of the mass of the rigid body. */
		real inverseMass;

		/**
		 * Holds the inverse of the body’s inertia tensor. The inertia
		 * tensor provided must not be degenerate (that would mean
		 * the body had zero inertia for spinning along one axis).
		 * As long as the tensor is finite, it will be invertible.
		 * The inverse tensor is used for similar reasons as those
		 * for the use of inverse mass.
		 *
		 * The inertia tensor, unlike the other variables that define
		 * a rigid body, is given in body space.
		 */
		Matrix3 inverseInertiaTensor;

		/** Holds the linear position of the rigid body in world space. */
		Vector3 position;

		/** Holds the angular orientation of the rigid body in world space. */
		Quaternion orientation;

		/** Holds the linear velocity of the rigid body in world space. */
		Vector3 velocity;

		/** Holds the angular velocity, or rotation, of the rigid body in world space. */
		Vector3 rotation;

		/**
		 * @name Derived Data
		 *
		 * These data members hold information that is derived from
		 * the other data in the class.
		 */
		 /*@{*/

		 /**
		  * Holds the inverse inertia tensor of the body in world
		  * space. The inverse inertia tensor member is specified in
		  * the body's local space.
		  *
		  * @see inverseInertiaTensor
		  */
		Matrix3 inverseInertiaTensorWorld;

		/**
		 * Holds a transform matrix for converting body space into world
		 * space and vice versa. This can be achieved by calling the
		 * getPointIn()Space functions.
		 */
		Matrix4 transformMatrix;

		/**
		 * Holds the accumulated force to be applied at the next
		 * integration step.
		 */
		Vector3 forceAccum;

		/**
		 * Holds the accumulated torque to be applied at the next
		 * integration step.
		 */
		Vector3 torqueAccum;

		/**
		  * Holds the acceleration of the rigid body.  This value
		  * can be used to set acceleration due to gravity (its primary
		  * use), or any other constant acceleration.
		  */
		Vector3 acceleration;

		/**
		 * Holds the linear acceleration of the rigid body, for the
		 * previous frame.
		 */
		Vector3 lastFrameAcceleration;

		/**
		 * A body can be put to sleep to avoid it being updated
		 * by the integration functions or affected by collisions
		 * with the world.
		 */
		bool isAwake;

	public:
		/**
		 * Calculates internal data from state data. This should be called
		 * after the body's state is altered directly (it is called
		 * automatically during integration). If you change the body's
		 * state and then intend to integrate before querying any data
		 * (such as the transform matrix), then you can omit this step.
		 */
		void calculateDerivedData();

		void setInertiaTensor(const Matrix3& inertiaTensor);

		/**
		 * Adds the given force to the center of mass of the rigid body.
		 * The force is expressed in world coordinates.
		 *
		 * @param force The force to apply.
		 */
		void addForce(const Vector3& force);

		/**
		 * Adds the given force to the given point on the rigid body.
		 * Both the force and the
		 * application point are given in world space. Because the
		 * force is not applied at the centre of mass, it may be split
		 * into both a force and torque.
		 *
		 * @param force The force to apply.
		 *
		 * @param point The location at which to apply the force, in
		 * world-coordinates.
		 */
		void addForceAtPoint(const Vector3& force, const Vector3& point);

		/**
		 * Adds the given force to the given point on the rigid body.
		 * The direction of the force is given in world coordinates,
		 * but the application point is given in body space. This is
		 * useful for spring forces, or other forces fixed to the
		 * body.
		 *
		 * @param force The force to apply.
		 *
		 * @param point The location at which to apply the force, in
		 * body-coordinates.
		 */
		void addForceAtBodyPoint(const Vector3& force, const Vector3& point);

		/**
		 * Clears the forces and torques in the accumulators. This will
		 * be called automatically after each intergration step.
		 */
		void clearAccumulators();

		/**
		 * Gets a transformation representing the rigid body's
		 * position and orientation.
		 *
		 * @note Transforming a vector by this matrix turns it from
		 * the body's local space to world space.
		 *
		 * @return The transform matrix for the rigid body.
		 */
		Matrix4 getTransform() const;

		/**
		 * Converts the given point from world space into the body's
		 * local space.
		 *
		 * @param point The point to covert, given in world space.
		 *
		 * @return The converted point, in local space.
		 */
		Vector3 getPointInLocalSpace(const Vector3& point) const;

		/**
		 * Converts the given point from world space into the body's
		 * local space.
		 *
		 * @param point The point to covert, given in local space.
		 *
		 * @return The converted point, in world space.
		 */
		Vector3 getPointInWorldSpace(const Vector3& point) const;

		/**
		 * Converts the given direction from world space into the
		 * body's local space.
		 *
		 * @note When a direction is converted between frames of
		 * reference, there is no translation required.
		 *
		 * @param direction The direction to covert, given in world
		 * space.
		 *
		 * @return The converted direction, in local space.
		 */
		Vector3 getDirectionInLocalSpace(const Vector3& direction) const;

		/**
		 * Converts the given direction from world space into the
		 * body's local space.
		 *
		 * @note When a direction is converted between frames of
		 * reference, there is no translation required.
		 *
		 * @param direction The direction to covert, given in local
		 * space.
		 *
		 * @return The converted direction, in world space.
		 */
		Vector3 getDirectionInWorldSpace(const Vector3& direction) const;
	};

} // namespace physics