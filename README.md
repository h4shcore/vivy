# VIVY

An **Image Viewer** made with **C++** and **SDL**.

### FEATURES:

- loads external images
- automatic sizing (need to make it more optimal)
- GPU rendering
- keyboard controls
- zooming
- event loop
- native windowing

> [!NOTE]
> You need **SDL** and **cmake** installed to **build**.

> [!TIP]
> use nix instead.
>
> ```sh
> nix-develop -c <bash or your fav shell>
> ```

### BUILD:

```sh
mkdir build
cd build
cmake ..
make
```

### USAGE:

```sh
./vivy <image-path>.jpg/.png
```
