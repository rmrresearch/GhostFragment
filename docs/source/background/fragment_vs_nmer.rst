###################
Fragments Vs N-Mers
###################

.. |n| replace:: :math:`n`
.. |m| replace:: :math:`m`

**********
Background
**********

TODO: List previous debates

********
Our Take
********

The unifying aspect of fragment based methods is that they break a supersystem
up into a set of subsystems, and then use the properties of the subsystems to
approximate the properties of the supersystem. As has been rightfully pointed
out a number of times, sub-/supersystem are somewhat relative terms. For
example, if one is looking at water dimer, it is natural to term the dimer the
supersystem and the natural (albeit not the only) choice for the subsystems are
the water monomers. However, it's entirely possible that the water dimer we just
considered actually stems from considerations of the three two-body interactions
in a water trimer; in this case that same water dimer is actually a subsystem.
The point is that the sub-/supersystem relationship is relative and contextually
dependent.

|n|-mers are defined as the union of |n| fragments. Hence |n|-mers and fragments
share a super/subsystem relation. So it's perhaps unsurprising that the terms
are relative. That said, in practice we find that there is an asymmetry to how
fragments and |n|-mers are treated, because of this asymmetry it is worth
exploring the distinction in more detail. Ultimately, the design of
GhostFragment assumes the user also cares about the distinction between |n|-mers
and fragments and treats them separately.

At some level every fragment-based method defines a fundamental set of subsets.
We term the elements of this subset fragments. Once you have defined fragments,
you always can define dimers, trimers, or in general |n|-mers (up to the number
of fragments) by taking unions of fragments. In practice, fragments tend to
contain atoms which are proximally close to each other (as determined by metrics
such as distance between atoms or number of bonds between atoms). With this
convention, a typical |n|-mer differs from a fragment in that the atoms
contained in the |n|-mer are not all close to each other.

So what's to stop us from treating the resulting |n|-mers as fragments? Put
another way, can we just treat the process of forming the |n|-mers as the last
step of a fragmentation method? The short answer is there's no reason we can't
treat the |n|-mers as fragments. In fact this realization was the key to
originally computing the energy with the GMBE. That said, what we usually care
about is accurately predicting the properties of the supersystem. So if the set
of fragments allows us to accurately predict the properties of the supersystem,
there's no reason to consider |n|-mers.

So why do we care about |n|-mers at all? The reason is simple, with nearly all
fragmentation methods limited to producing fragments comprised of proximally
close atoms, we need a way to build in long-distance interactions. At the moment
there's really only two ways to do this: large overlapping fragments, or by
relying on |n|-mers. The former option is essentially a brute-force approach,
i.e., the fragments need to be so large that every important many-body
interaction appears in at least one fragment, furthermore the size of the
fragments must be large enough that the chemical environment around the
interaction is sufficiently similar to the supersystem. On the contrary by
relying on |n|-mers, we can have small fragments and systematically grow the
subsystem sizes so that they include the important many-body interactions with
minimal additional overhead.

Since most fragment-based methods are going to need to use |n|-mers, the design
of GhostFragment needs to consider them. While it would be possible to hide the
formation of |n|-mers under the fragmentation method, keeping track of  where
the |n|-mers come from has a number of algorithmic advantages:

- re-using |m|-mer (|m| < |n|) guesses
- easier evaluation of intersections
