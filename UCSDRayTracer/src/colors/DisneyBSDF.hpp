//
//  DisneyBSDF.hpp
//  UCSDRayTracer
//
//  Created by Brendan Mulcahey on 7/19/23.
//

#ifndef DisneyBSDF_hpp
#define DisneyBSDF_hpp

#include <stdio.h>
#include "texture.hpp"

/*
struct DisneyDiffuse {
    Texture<Spectrum> base_color;
    Texture<Real> roughness;
    Texture<Real> subsurface;

using Material = std::variant<Lambertian,
                           RoughPlastic,
                           RoughDielectric,
                           DisneyDiffuse,
                           DisneyMetal,
                           DisneyGlass,
                           DisneyClearcoat,
                           DisneySheen,
                           DisneyBSDF>;
struct eval_op {
    spectrum operator()(const Lambertian &bsdf) const;
    spectrum operator()(const RoughPlastic &bsdf) const;
    spectrum operator()(const RoughDielectric &bsdf) const;
    spectrum operator()(const DisneyDiffuse &bsdf) const;
    spectrum operator()(const DisneyMetal &bsdf) const;
    spectrum operator()(const DisneyGlass &bsdf) const;
    spectrum operator()(const DisneyClearcoat &bsdf) const;
    spectrum operator()(const DisneySheen &bsdf) const;
    spectrum operator()(const DisneyBSDF &bsdf) const;

 const vector3 &dir_in;
 const Vector3 &dir_out;
 const PathVertex &vertex;
 const TexturePool &texture_pool;
 const TransportDirection &dir;
};
struct pdf_sample_bsdf_op {
 Real operator()(const Lambertian &bsdf) const;
 Real operator()(const RoughPlastic &bsdf) const;
 Real operator()(const RoughDielectric &bsdf) const;
 Real operator()(const DisneyDiffuse &bsdf) const;
 // ...
 const Vector3 &dir_in;
 const Vector3 &dir_out;
 const PathVertex &vertex;
 const TexturePool &texture_pool;
 const TransportDirection &dir;
};
struct sample_bsdf_op {
 std::optional<BSDFSampleRecord> operator()(const Lambertian &bsdf) const;
 std::optional<BSDFSampleRecord> operator()(const RoughPlastic &bsdf) const;
 std::optional<BSDFSampleRecord> operator()(const RoughDielectric &bsdf) const;
 std::optional<BSDFSampleRecord> operator()(const DisneyDiffuse &bsdf) const;
 // ...
 const Vector3 &dir_in;
 const PathVertex &vertex;
 const TexturePool &texture_pool;
 const Vector2 &rnd_param_uv;
 const Real &rnd_param_w;
 const TransportDirection &dir;
};
*/
#endif /* DisneyBSDF_hpp */


