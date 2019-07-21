
#ifndef MI_CSS_C
#define MI_CSS_C

G_MODULE_EXPORT void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{

	gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
	if (GTK_IS_CONTAINER (widget))
	{
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
	}

}

#endif
