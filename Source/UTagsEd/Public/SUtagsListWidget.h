#pragma once

#include "SlateBasics.h"
#include "SSearchBox.h"
//#include "SUtagsDetailsTreeWidget.h"
class SUtagsListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUtagsListWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
	FReply ButtonPressed();

	/* Adds a new textbox with the string to the list */
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedRef<ITableRow> OnGenerateRowForEditableList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
	//	TSharedRef SOnGenerateWidgetForList(TSharedPtr<FString> Item);

	/* The list of strings containing the name and TagType */
	TArray<TSharedPtr<FString>> ItemsFirstColumn;

	/* The list of strings */
	TArray<TSharedPtr<FString>> ItemsSecondColumn;

	/* The actual UI list */
	TSharedPtr< SListView< TSharedPtr<FString> > >  FirstViewWidget;
	TSharedPtr< SListView< TSharedPtr<FString> > > SecondViewWidget;
//	TSharedPtr<class SUtagsDetailsTreeWidget> DetailsTreeWidget;
private:
/** Handles changing the filter string text box text. */
	void HandleFilterStringTextChanged(const FText& NewText)
	{
		//Filter->SetFilterString(NewText.ToString());
	}
};

