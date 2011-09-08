#ifndef SDF_LOADER_H
#define SDF_LOADER_H


class sdf_loader
{
    public:
        sdf_loader();
        ~sdf_loader();
        scene loader(std::string const& sdf) const&;

    private:
};

#endif // SDF_LOADER_H
