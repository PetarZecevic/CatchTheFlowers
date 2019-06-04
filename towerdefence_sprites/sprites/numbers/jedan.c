/* GIMP RGBA C-Source image dump (jedan.c) */

static const struct {
  guint  	 width;
  guint  	 height;
  guint  	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  guint8 	 pixel_data[16 * 16 * 4 + 1];
} gimp_image = {
  16, 16, 4,
  "\371\377\377\377\371\377\377\377\372\377\377\377\373\377\377\377\374\377"
  "\377\377\374\377\377\377\374\377\377\377\373\377\377\377\367\376\377\377"
  "\363\376\377\377\360\376\377\377\357\377\377\377\360\377\377\377\360\377"
  "\377\377\361\377\377\377\361\376\377\377\371\377\377\377\372\377\377\377"
  "\372\377\377\377\373\377\377\377\374\377\377\377\374\377\377\377\374\377"
  "\377\377\372\377\377\377\367\377\377\377\363\377\377\377\361\377\377\377"
  "\360\377\377\377\360\377\377\377\360\377\377\377\361\376\377\377\360\376"
  "\377\377\372\377\377\377\372\377\377\377\373\377\377\377\373\377\377\377"
  "\374\377\377\377\374\377\377\377\357*\012\377\357*\012\377\357*\012\377\357"
  "*\012\377\357*\012\377\360\377\377\377\360\377\377\377\361\376\377\377\360"
  "\376\377\377\360\375\376\377\373\377\377\377\373\377\377\377\373\377\377"
  "\377\374\377\377\377\374\377\377\377\374\377\377\377\357*\012\377\357*\012"
  "\377\357*\012\377\357*\012\377\357*\012\377\360\377\377\377\360\377\377\377"
  "\361\376\377\377\361\376\376\377\360\375\376\377\374\377\377\377\374\377"
  "\377\377\374\377\377\377\357*\012\377\357*\012\377\357*\012\377\357*\012\377"
  "\374\022\002\377\371\033\004\377\357*\012\377\357*\012\377\361\377\377\377\361\377"
  "\377\377\361\377\377\377\361\376\377\377\361\376\376\377\375\376\377\377"
  "\375\376\377\377\375\377\377\377\357*\012\377\357*\012\377\357*\012\377\366"
  "\037\005\377\374\017\002\377\371\033\004\377\357*\012\377\357*\012\377\361\377\377\377"
  "\361\377\377\377\361\377\377\377\362\377\377\377\362\376\377\377\376\376"
  "\377\377\376\376\377\377\376\376\377\377\357*\012\377\357*\012\377\357*\012"
  "\377\357*\012\377\372\024\003\377\371\032\004\377\357*\012\377\357*\012\377\360\377"
  "\377\377\361\377\377\377\361\377\377\377\362\377\377\377\362\377\377\377"
  "\376\376\377\377\376\376\377\377\376\376\377\377\376\376\377\377\376\377"
  "\377\377\375\377\377\377\357*\012\377\371\030\004\377\370\033\004\377\357*\012\377"
  "\357*\012\377\361\377\377\377\361\377\377\377\361\377\377\377\362\377\377"
  "\377\362\377\377\377\376\376\377\377\376\376\377\377\376\376\377\377\376"
  "\377\377\377\376\377\377\377\375\377\377\377\357*\012\377\370\031\004\377\370"
  "\034\004\377\357*\012\377\357*\012\377\361\377\377\377\361\377\377\377\362\377"
  "\377\377\362\377\377\377\362\377\377\377\375\376\377\377\375\377\377\377"
  "\375\377\377\377\375\377\377\377\375\377\377\377\375\377\377\377\357*\012"
  "\377\370\031\004\377\370\035\004\377\357*\012\377\357*\012\377\362\377\377\377\362"
  "\377\377\377\362\377\377\377\363\376\377\377\363\376\376\377\375\376\377"
  "\377\375\377\377\377\375\377\377\377\375\377\377\377\375\377\377\377\375"
  "\377\377\377\352\061\015\377\371\030\004\377\371\033\003\377\357*\012\377\357*\012"
  "\377\362\377\377\377\362\377\377\377\363\376\376\377\363\376\376\377\363"
  "\375\375\377\376\376\377\377\376\376\377\377\376\376\377\377\376\377\377"
  "\377\376\377\377\377\357*\012\377\357*\012\377\372\025\003\377\372\026\002\377\357"
  "-\007\377\357*\012\377\363\377\377\377\363\376\377\377\363\376\376\377\362\374"
  "\375\377\362\373\374\377\376\376\377\377\376\376\377\377\376\376\377\377"
  "\357*\012\377\357*\012\377\357*\012\377\360,\011\377\365\"\006\377\365\040\006\377"
  "\360(\011\377\357*\012\377\357*\012\377\357*\012\377\363\375\375\377\362\373"
  "\373\377\360\370\371\377\377\376\377\377\377\376\377\377\377\376\377\377"
  "\357*\012\377\357*\012\377\357*\012\377\357*\012\377\357*\012\377\357*\012\377"
  "\357*\012\377\357*\012\377\357*\012\377\357*\012\377\363\375\374\377\362\373"
  "\372\377\360\370\366\377\377\376\377\377\377\376\377\377\377\376\377\377"
  "\377\376\377\377\376\377\377\377\376\377\377\377\375\377\377\377\373\377"
  "\377\377\371\377\377\377\366\377\377\377\364\377\377\377\364\377\376\377"
  "\364\376\375\377\364\375\374\377\364\374\370\377\362\371\364\377\377\376"
  "\377\377\377\376\377\377\377\376\377\377\377\376\377\377\376\376\377\377"
  "\376\377\377\377\374\377\377\377\373\377\377\377\371\377\377\377\366\377"
  "\377\377\365\377\377\377\365\377\376\377\365\376\375\377\365\376\373\377"
  "\365\375\370\377\365\373\363\377",
};

