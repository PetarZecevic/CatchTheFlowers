/* GIMP RGBA C-Source image dump (dva.c) */

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
  "\377\377\372\377\377\377\372\377\377\377\373\377\377\377\365!\006\377\365!"
  "\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377"
  "\365!\006\377\365!\006\377\361\376\377\377\360\376\377\377\360\375\376\377\373"
  "\377\377\377\373\377\377\377\373\377\377\377\365!\006\377\365!\006\377\365!\006"
  "\377\365!\006\377\365!\006\377\365!\006\377\362'\010\377\365\"\007\377\355-\013\377"
  "\365!\006\377\361\376\377\377\361\376\376\377\360\375\376\377\374\377\377\377"
  "\374\377\377\377\374\377\377\377\375\377\377\377\375\377\377\377\375\377"
  "\377\377\374\377\377\377\372\377\377\377\365!\006\377\364%\007\377\373\023\003\377"
  "\365!\006\377\365!\006\377\361\377\377\377\361\376\377\377\361\376\376\377\375"
  "\376\377\377\375\376\377\377\375\377\377\377\375\377\377\377\375\377\377"
  "\377\375\377\377\377\374\377\377\377\372\377\377\377\365!\006\377\361(\012\377"
  "\372\024\003\377\365\040\006\377\365!\006\377\361\377\377\377\362\377\377\377\362"
  "\376\377\377\376\376\377\377\376\376\377\377\376\376\377\377\376\376\377"
  "\377\376\377\377\377\375\377\377\377\374\377\377\377\372\377\377\377\365"
  "!\006\377\360\"\013\377\372\022\003\377\365\"\006\377\365!\006\377\361\377\377\377"
  "\362\377\377\377\362\377\377\377\376\376\377\377\376\376\377\377\376\376"
  "\377\377\376\376\377\377\376\377\377\377\375\377\377\377\374\377\377\377"
  "\372\377\377\377\365!\006\377\364\031\011\377\373\021\003\377\365'\007\377\365!\006"
  "\377\361\377\377\377\362\377\377\377\362\377\377\377\376\376\377\377\376"
  "\376\377\377\376\376\377\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377"
  "\365!\006\377\365!\006\377\363\037\010\377\365\"\006\377\356\066\012\377\365!\006\377"
  "\362\377\377\377\362\377\377\377\362\377\377\377\375\376\377\377\375\377"
  "\377\377\375\377\377\377\365!\006\377\355+\013\377\365\035\007\377\363\036\011\377"
  "\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\362\377"
  "\377\377\363\376\377\377\363\376\376\377\375\376\377\377\375\377\377\377"
  "\375\377\377\377\365!\006\377\365\"\006\377\373\021\002\377\365\036\006\377\365!\006"
  "\377\370\377\377\377\365\377\377\377\363\377\377\377\362\377\377\377\362"
  "\377\377\377\363\376\376\377\363\376\376\377\363\375\375\377\376\376\377"
  "\377\376\376\377\377\376\376\377\377\365!\006\377\365\"\006\377\373\021\002\377"
  "\365\036\006\377\365!\006\377\371\377\377\377\366\377\377\377\364\377\377\377"
  "\363\377\377\377\363\376\377\377\363\376\376\377\362\374\375\377\362\373"
  "\374\377\376\376\377\377\376\376\377\377\376\376\377\377\365!\006\377\365!"
  "\006\377\365$\006\377\362'\010\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377"
  "\365!\006\377\365!\006\377\363\375\375\377\362\373\373\377\360\370\371\377\377"
  "\376\377\377\377\376\377\377\377\376\377\377\365!\006\377\365!\006\377\365!\006"
  "\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365!\006\377\365"
  "!\006\377\363\375\374\377\362\373\372\377\360\370\366\377\377\376\377\377\377"
  "\376\377\377\377\376\377\377\377\376\377\377\376\377\377\377\376\377\377"
  "\377\375\377\377\377\373\377\377\377\371\377\377\377\366\377\377\377\364"
  "\377\377\377\364\377\376\377\364\376\375\377\364\375\374\377\364\374\370"
  "\377\362\371\364\377\377\376\377\377\377\376\377\377\377\376\377\377\377"
  "\376\377\377\376\376\377\377\376\377\377\377\374\377\377\377\373\377\377"
  "\377\371\377\377\377\366\377\377\377\365\377\377\377\365\377\376\377\365"
  "\376\375\377\365\376\373\377\365\375\370\377\365\373\363\377",
};

