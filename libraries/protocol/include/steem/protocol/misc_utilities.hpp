#pragma once

namespace clout { namespace protocol {

enum curve_id
{
   quadratic,
   bounded,
   linear,
   square_root,
   convergent_linear,
   convergent_square_root
};

} } // clout::utilities


FC_REFLECT_ENUM(
   clout::protocol::curve_id,
   (quadratic)
   (bounded)
   (linear)
   (square_root)
   (convergent_linear)
   (convergent_square_root)
)
