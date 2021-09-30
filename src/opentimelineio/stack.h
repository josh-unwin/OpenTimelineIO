#pragma once

#include "opentimelineio/version.h"
#include "opentimelineio/composition.h"

namespace opentimelineio { namespace OPENTIMELINEIO_VERSION  {
    
class Clip;

class Stack : public Composition {
public:
    struct Schema {
        static auto constexpr name = "Stack";
        static int constexpr version = 1;
    };

    using Parent = Composition;

    Stack(
            std::string const& name = std::string(),
            optional<TimeRange> const& source_range = nullopt,
            AnyDictionary const& metadata = AnyDictionary(),
            std::vector<Effect*> const& effects = std::vector<Effect*>(),
            std::vector<Marker*> const& markers = std::vector<Marker*>());

    virtual TimeRange range_of_child_at_index(int index, ErrorStatus* error_status) const;
    virtual TimeRange trimmed_range_of_child_at_index(int index, ErrorStatus* error_status) const;
    virtual TimeRange available_range(ErrorStatus* error_status) const;

    virtual std::map<Composable*, TimeRange> range_of_all_children(ErrorStatus* error_status) const;

    optional<Imath::Box2d> available_image_bounds(ErrorStatus* error_status) const;

    // Return a vector of clips.
    //
    // An optional search_range may be provided to limit the search.
    std::vector<Retainer<Clip> > clip_if(
        ErrorStatus* error_status,
        optional<TimeRange> const& search_range = nullopt,
        bool shallow_search = false) const;

protected:
    virtual ~Stack();

    virtual std::string const& composition_kind() const;

    virtual bool read_from(Reader&);
    virtual void write_to(Writer&) const;

private:

};

} }
