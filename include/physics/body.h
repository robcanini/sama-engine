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

		/**
		 * Holds the amount of damping applied to linear
		 * motion.  Damping is required to remove energy added
		 * through numerical instability in the integrator.
		 */
		real linearDamping;

		/**
		 * Holds the amount of damping applied to angular
		 * motion.  Damping is required to remove energy added
		 * through numerical instability in the integrator.
		 */
		real angularDamping;

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
		 * Holds the amount of motion of the body. This is a recency
		 * weighted mean that can be used to put a body to sleap.
		 */
		real motion;

		/**
		 * A body can be put to sleep to avoid it being updated
		 * by the integration functions or affected by collisions
		 * with the world.
		 */
		bool isAwake;

		/**
		 * Some bodies may never be allowed to fall asleep.
		 * User controlled bodies, for example, should be
		 * always awake.
		 */
		bool canSleep;

	public:
		/**
		 * Calculates internal data from state data. This should be called
		 * after the body's state is altered directly (it is called
		 * automatically during integration). If you change the body's
		 * state and then intend to integrate before querying any data
		 * (such as the transform matrix), then you can omit this step.
		 */
		void calculateDerivedData();

		/**
		 * Integrates the rigid body forward in time by the given amount.
		 * This function uses a Newton-Euler integration method, which is a
		 * linear approximation to the correct integral. For this reason it
		 * may be inaccurate in some cases.
		 */
		void integrate(real duration);

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
		 * Sets the velocity of the rigid body.
		 *
		 * @param velocity The new velocity of the rigid body. The
		 * velocity is given in world space.
		 */
		void setVelocity(const Vector3& velocity);

		/**
		 * Sets the velocity of the rigid body by component. The
		 * velocity is given in world space.
		 *
		 * @param x The x coordinate of the new velocity of the rigid
		 * body.
		 *
		 * @param y The y coordinate of the new velocity of the rigid
		 * body.
		 *
		 * @param z The z coordinate of the new velocity of the rigid
		 * body.
		 */
		void setVelocity(const real x, const real y, const real z);

		/**
		 * Fills the given vector with the velocity of the rigid body.
		 *
		 * @param velocity A pointer to a vector into which to write
		 * the velocity. The velocity is given in world local space.
		 */
		void getVelocity(Vector3* velocity) const;

		/**
		 * Gets the velocity of the rigid body.
		 *
		 * @return The velocity of the rigid body. The velocity is
		 * given in world local space.
		 */
		Vector3 getVelocity() const;

		/**
		 * Applies the given change in velocity.
		 */
		void addVelocity(const Vector3& deltaVelocity);

		/**
		 * Sets the rotation of the rigid body.
		 *
		 * @param rotation The new rotation of the rigid body. The
		 * rotation is given in world space.
		 */
		void setRotation(const Vector3& rotation);

		/**
		 * Sets the rotation of the rigid body by component. The
		 * rotation is given in world space.
		 *
		 * @param x The x coordinate of the new rotation of the rigid
		 * body.
		 *
		 * @param y The y coordinate of the new rotation of the rigid
		 * body.
		 *
		 * @param z The z coordinate of the new rotation of the rigid
		 * body.
		 */
		void setRotation(const real x, const real y, const real z);

		/**
		 * Fills the given vector with the rotation of the rigid body.
		 *
		 * @param rotation A pointer to a vector into which to write
		 * the rotation. The rotation is given in world local space.
		 */
		void getRotation(Vector3* rotation) const;

		/**
		 * Gets the rotation of the rigid body.
		 *
		 * @return The rotation of the rigid body. The rotation is
		 * given in world local space.
		 */
		Vector3 getRotation() const;

		/**
		 * Applies the given change in rotation.
		 */
		void addRotation(const Vector3& deltaRotation);

		/**
		 * Returns true if the body is awake and responding to
		 * integration.
		 *
		 * @return The awake state of the body.
		 */
		bool getAwake() const
		{
			return isAwake;
		}

		/**
		 * Sets the awake state of the body. If the body is set to be
		 * not awake, then its velocities are also cancelled, since
		 * a moving body that is not awake can cause problems in the
		 * simulation.
		 *
		 * @param awake The new awake state of the body.
		 */
		void setAwake(const bool awake = true);

		/**
		 * Returns true if the body is allowed to go to sleep at
		 * any time.
		 */
		bool getCanSleep() const
		{
			return canSleep;
		}

		/**
		 * Sets whether the body is ever allowed to go to sleep. Bodies
		 * under the player's control, or for which the set of
		 * transient forces applied each frame are not predictable,
		 * should be kept awake.
		 *
		 * @param canSleep Whether the body can now be put to sleep.
		 */
		void setCanSleep(const bool canSleep = true);

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

		/**
		 * Sets the mass of the rigid body.
		 *
		 * @param mass The new mass of the body. This may not be zero.
		 * Small masses can produce unstable rigid bodies under
		 * simulation.
		 *
		 * @warning This invalidates internal data for the rigid body.
		 * Either an integration function, or the calculateInternals
		 * function should be called before trying to get any settings
		 * from the rigid body.
		 */
		void setMass(const real mass);

		/**
		 * Gets the mass of the rigid body.
		 *
		 * @return The current mass of the rigid body.
		 */
		real getMass() const;

		/**
		 * Sets the inverse mass of the rigid body.
		 *
		 * @param inverseMass The new inverse mass of the body. This
		 * may be zero, for a body with infinite mass
		 * (i.e. unmovable).
		 *
		 * @warning This invalidates internal data for the rigid body.
		 * Either an integration function, or the calculateInternals
		 * function should be called before trying to get any settings
		 * from the rigid body.
		 */
		void setInverseMass(const real inverseMass);

		/**
		 * Gets the inverse mass of the rigid body.
		 *
		 * @return The current inverse mass of the rigid body.
		 */
		real getInverseMass() const;

		/**
		 * Returns true if the mass of the body is not-infinite.
		 */
		bool hasFiniteMass() const;

		/**
		 * Sets both linear and angular damping in one function call.
		 *
		 * @param linearDamping The speed that velocity is shed from
		 * the rigid body.
		 *
		 * @param angularDamping The speed that rotation is shed from
		 * the rigid body.
		 *
		 * @see setLinearDamping
		 * @see setAngularDamping
		 */
		void setDamping(const real linearDamping, const real angularDamping);

		/**
		 * Sets the linear damping for the rigid body.
		 *
		 * @param linearDamping The speed that velocity is shed from
		 * the rigid body.
		 *
		 * @see setAngularDamping
		 */
		void setLinearDamping(const real linearDamping);

		/**
		 * Gets the current linear damping value.
		 *
		 * @return The current linear damping value.
		 */
		real getLinearDamping() const;

		/**
		 * Sets the angular damping for the rigid body.
		 *
		 * @param angularDamping The speed that rotation is shed from
		 * the rigid body.
		 *
		 * @see setLinearDamping
		 */
		void setAngularDamping(const real angularDamping);

		/**
		 * Gets the current angular damping value.
		 *
		 * @return The current angular damping value.
		 */
		real getAngularDamping() const;
	};

} // namespace physics